#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
// log
#include "cinder/Log.h"
// Spout
#include "GifEncoder.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class _TBOX_PREFIX_App : public App {

public:
	_TBOX_PREFIX_App();
	void mouseMove(MouseEvent event) override;
	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;
	void fileDrop(FileDropEvent event) override;
	void update() override;
	void draw() override;
	void cleanup() override;
private:
	vector <ci::gl::Texture2dRef> txs; // for previewing
	vector <GifEncoder::GifFrame *> pxs;

	int frameW, frameH;
	int nFrames;

	GifEncoder gifEncoder;
	void onGifSaved(string & fileName);
	void captureFrame();
	ci::gl::Texture2dRef frame;
	string						mPath;
};


_TBOX_PREFIX_App::_TBOX_PREFIX_App()
{
	nFrames = 0;
	frameW = 320;
	frameH = 240;
	//frame= ci::gl::Texture::create(frameW, frameH, ci::gl::Texture::Format().loadTopDown(true));
	frame = ci::gl::Texture::create(loadImage(loadAsset("0.jpg")), ci::gl::Texture::Format().loadTopDown(true));

	gifEncoder.setup(frameW, frameH, .25, 256);
}

void _TBOX_PREFIX_App::fileDrop(FileDropEvent event)
{

}
void _TBOX_PREFIX_App::update()
{

}

void _TBOX_PREFIX_App::mouseMove(MouseEvent event)
{

}
void _TBOX_PREFIX_App::mouseDown(MouseEvent event)
{

}
void _TBOX_PREFIX_App::cleanup()
{
	gifEncoder.exit();
}
void _TBOX_PREFIX_App::mouseUp(MouseEvent event)
{

}

void _TBOX_PREFIX_App::keyDown(KeyEvent event)
{
	switch (event.getCode()) {
	case KeyEvent::KEY_SPACE:
		captureFrame();
		break;
	case KeyEvent::KEY_s:
		cout << "start saving\n" << endl;
		gifEncoder.save(toString(getElapsedFrames()) + ".gif");
		break;
	case KeyEvent::KEY_ESCAPE:
		// quit the application
		quit();
		break;

	default:
		break;
	}
}
void _TBOX_PREFIX_App::keyUp(KeyEvent event)
{

}

void _TBOX_PREFIX_App::draw()
{
	gl::clear(Color::black());
	gl::setMatricesWindow(toPixels(getWindowSize()), false);
	for (int i = 0; i < nFrames; i++) {
		gl::draw(txs[i], Rectf(i* frameW, 0, frameW, frameH));
	}

}
void _TBOX_PREFIX_App::onGifSaved(string &fileName) {
	cout << "gif saved as " << fileName << endl;
}
void _TBOX_PREFIX_App::captureFrame() {
	gifEncoder.addFrame(frame);
	//gifEncoder.addFramePx(
	//	&vid.getPixels(),
	//	vid.getWidth(),
	//	vid.getHeight(),
	//	vid.getPixelsRef().getBitsPerPixel(),
	//	.1f
	//);

	txs.push_back(frame);

	nFrames++;
}

void prepareSettings(App::Settings *settings)
{
	settings->setWindowSize(640, 480);
}

CINDER_APP(_TBOX_PREFIX_App, RendererGl, prepareSettings)
