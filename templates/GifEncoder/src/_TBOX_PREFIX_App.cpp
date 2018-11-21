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
};


_TBOX_PREFIX_App::_TBOX_PREFIX_App()
{
	nFrames = 0;
	frameW = 320;
	frameH = 240;

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
		gifEncoder.save("test.gif");
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
		//txs[i]->draw(i* (frameW / 2 + 5), frameH, frameW / 2, frameH / 2);
	}

}
void _TBOX_PREFIX_App::onGifSaved(string &fileName) {
	cout << "gif saved as " << fileName << endl;
}
void _TBOX_PREFIX_App::captureFrame() {
	//gifEncoder.addFramePx(
	//	&vid.getPixels(),
	//	vid.getWidth(),
	//	vid.getHeight(),
	//	vid.getPixelsRef().getBitsPerPixel(),
	//	.1f
	//);

	//ci::gl::Texture2dRef tx = new ofTexture();
	//tx->allocate(frameW, frameH, GL_RGB);
	//tx->loadData(vid.getPixels(), GL_RGB);//, frameW, frameH
	//txs.push_back(tx);

	nFrames++;
}

void prepareSettings(App::Settings *settings)
{
	settings->setWindowSize(640, 480);
}

CINDER_APP(_TBOX_PREFIX_App, RendererGl, prepareSettings)
