

#include "MediaOp.h"

MediaOp::MediaOp()
{

	movies.clear();

	// TODO: maximum texture size of videocard should be queried from OpenGL
	mMaxSize = 2048;
}

MediaOp::~MediaOp(void)
{
	// gracefully abort current threads:
	deque<boost::shared_ptr<thread> >::iterator itr;
	// tell all threads to stop as soon as possible
	for(itr=mThreads.begin();itr!=mThreads.end();++itr)
		(*itr)->interrupt();
	// wait for all threads to finish
	for(itr=mThreads.begin();itr!=mThreads.end();++itr)
		(*itr)->join();

	mThreads.clear();
}

void MediaOp::setup()
{
	currentMovieNumber = 0;
}

void MediaOp::setMediaFilePaths(	std::vector<std::string> &mediaFilePaths){
	this->mediaFilePaths = mediaFilePaths;
}

void MediaOp::update(uint videoNumber)
{
	// remove finished threads
	deque<boost::shared_ptr<boost::thread> >::iterator itr;
	for(itr=mThreads.begin();itr!=mThreads.end();)
	{
		if( (*itr)->timed_join<posix_time::milliseconds>(posix_time::milliseconds(1)) )
			itr = mThreads.erase(itr);
		else
			++itr;
	}

	if (mThreads.empty() && !movies.empty() && videoNumber<movies.size()){
		if (currentMovieNumber != videoNumber){
			console() << "video number "<<videoNumber << endl;
		}
		currentMovieNumber = 0;//videoNumber;
	}
}

void MediaOp::draw()
{
	// draw texture if it exists
	if(mTexture)
	{
		gl::color( Color::white() );
		gl::draw(mTexture);
	}

	// draw spinning wait cursor while loading
	if(!mThreads.empty())
	{
		int segments = 10;
		float radius = 25.0f;
		float size = 5.0f;
		float alpha = (float) getElapsedSeconds() - (int) getElapsedSeconds();
		Vec2f center = 0.5f * Vec2f(getSize());

		gl::enableAlphaBlending();
		for(int i=0;i<segments;++i)
		{
			float angle = i * toRadians(-360.0f / segments);
			Vec2f pt = center + radius * Vec2f( cosf(angle), sinf(angle) );

			gl::color( ColorAf(1.0f, 1.0f, 1.0f, 1.0f - alpha) );
			gl::drawSolidCircle(pt, size);

			alpha += 1.0f / segments;
			if(alpha > 1.0f) alpha -= 1.0f;
		}
		gl::disableAlphaBlending();
	}
}

void MediaOp::load()
{
	deque<boost::shared_ptr<boost::thread> >::iterator itr;
	for(itr=mThreads.begin();itr!=mThreads.end();++itr)
		(*itr)->interrupt();

	for( std::vector<std::string>::iterator item = mediaFilePaths.begin(); item != mediaFilePaths.end(); ++item ){
		//mThreads.push_back(boost::shared_ptr<thread>(new thread(&MediaLoader::threadLoad, this, *item)) );
		threadLoad(*item);
	}
}

Vec2i MediaOp::getSize()
{
	return Vec2i(100,100);
}

bool MediaOp::hasCurrentMovie(){
	currentMovieNumber = 0;
	return !movies.empty() &&  currentMovieNumber<  movies.size();
}

qtime::MovieGl MediaOp::getCurrentMovie(){
	currentMovieNumber = 0;
	qtime::MovieGl video  = movies[currentMovieNumber];

	if (video.checkPlayable() && !video.isPlaying()) {
		video.play();
		video.setLoop();
	}
	return video;
}

void MediaOp::threadLoad(const string &url)
{
	// copy to main thread
	moviesMutex.lock();
	qtime::MovieGl video;

	console() << getElapsedSeconds() << ": Loading:" << url << endl;

	try { 
		// try to load from FILE
		video = qtime::MovieGl( url );
		console() << getElapsedSeconds() << ":" << "Loaded:" << url << endl;
	}
	catch(...) { 
		console() << getElapsedSeconds() << ":" << "Could not load:" << url << endl;
		try {
			// try to load from URL
			video = qtime::MovieGl( ci::loadUrl( Url(url) ) );
			console() << getElapsedSeconds() << ":" << "Url loaded successfully:" << url << endl;
		}
		catch(...) {
			// both attempts to load the url failed
			console() << getElapsedSeconds() << ":" << "Failed to load:" << url << endl;
			return;
		}
	}

	try { 
		boost::this_thread::interruption_point();
	}
	catch(boost::thread_interrupted) {
		console() << getElapsedSeconds() << ":" << "Interruption detected, exiting..." << endl;
		// exit the thread
		return;
	}

	// resize
	Area source = Area(0, 0, (int)video.getWidth(), (int)video.getHeight());
	Area dest(0, 0, mMaxSize, mMaxSize);
	Area fit = Area::proportionalFit(source, dest, false, false);
		
	movies.push_back(video);

	console() << getElapsedSeconds() << ":" << "Added file " << url << " "<< movies.size()<<endl;
	moviesMutex.unlock();
}

gl::Texture MediaOp::getTexture() const
{
    return mTexture;
}

void MediaOp::update()
{
	if (hasCurrentMovie()){
		mTexture = getCurrentMovie().getTexture();
	}
}




