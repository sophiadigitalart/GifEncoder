#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

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
	void cleanUp() override;
private:
	vector <ofTexture *> txs; // for previewing
	vector <GifEncoder::GifFrame *> pxs;

	int frameW, frameH;
	int nFrames;

	ofxGifEncoder gifEncoder;
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
void _TBOX_PREFIX_App::cleanUp()
{
	gifEncoder.exit();
}
void _TBOX_PREFIX_App::mouseUp(MouseEvent event)
{
	
}

void _TBOX_PREFIX_App::keyDown(KeyEvent event)
{
		switch (event.key) {
	case ' ':
		captureFrame();
		break;
	case 's':
		cout << "start saving\n" << endl;
		gifEncoder.save("test.gif");
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
	

	//gl::setMatricesWindow(toPixels(getWindowSize()),false);
	gl::setMatricesWindow(mSDASettings->mRenderWidth, mSDASettings->mRenderHeight, false);
	gl::draw(mSDASession->getMixTexture(), getWindowBounds());
	for (int i = 0; i < nFrames; i++) {
		txs[i]->draw(i* (frameW / 2 + 5), frameH, frameW / 2, frameH / 2);
	}

	ofEnableAlphaBlending();
	ofDisableAlphaBlending();
	ofDrawBitmapString("KEYS\n----\nspacebar: capture frame\ns: save gif", frameW + 10, 20);

}
void _TBOX_PREFIX_App::onGifSaved(string &fileName) {
	cout << "gif saved as " << fileName << endl;
}
void _TBOX_PREFIX_App::captureFrame() {
	gifEncoder.addFramePx(
		&vid.getPixels(),
		vid.getWidth(),
		vid.getHeight(),
		vid.getPixelsRef().getBitsPerPixel(),
		.1f
	);

	ofTexture * tx = new ofTexture();
	tx->allocate(frameW, frameH, GL_RGB);
	tx->loadData(vid.getPixels(), GL_RGB);//, frameW, frameH
	txs.push_back(tx);

	nFrames++;
}
void _TBOX_PREFIX_App::captureFrame() {
	gifEncoder.addFramePx(
		&vid.getPixels(),
		vid.getWidth(),
		vid.getHeight(),
		vid.getPixelsRef().getBitsPerPixel(),
		.1f
	);

	ofTexture * tx = new ofTexture();
	tx->allocate(frameW, frameH, GL_RGB);
	tx->loadData(vid.getPixels(), GL_RGB);//, frameW, frameH
	txs.push_back(tx);

	nFrames++;
}
void prepareSettings(App::Settings *settings)
{
	settings->setWindowSize(640, 480);
}

CINDER_APP(_TBOX_PREFIX_App, RendererGl, prepareSettings)
