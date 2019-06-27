#include "plugin.hpp"
#include "BidooComponents.hpp"
#include <math.h>

using namespace std;

struct LOURDE : Module {
	enum ParamIds {
		WEIGHT1,
		WEIGHT2,
		WEIGHT3,
		OUTFLOOR,
		NUM_PARAMS
	};
	enum InputIds {
		IN1,
		IN2,
		IN3,
    INWEIGHT1,
		INWEIGHT2,
		INWEIGHT3,
    INFLOOR,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};


	LOURDE() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(WEIGHT1, -5.0f, 5.0f, 0.0f);
    configParam(WEIGHT2, -5.0f, 5.0f, 0.0f);
    configParam(WEIGHT3, -5.0f, 5.0f, 0.0f);
    configParam(OUTFLOOR, -10.0f, 10.0f, 0.0f);
  }

	void process(const ProcessArgs &args) override;
};


void LOURDE::process(const ProcessArgs &args) {
  float sum = clamp(params[WEIGHT1].value+inputs[INWEIGHT1].value,-5.0f,5.0f)*inputs[IN1].value + clamp(params[WEIGHT2].value+inputs[INWEIGHT2].value,-5.0f,5.0f)*inputs[IN2].value + clamp(params[WEIGHT3].value+inputs[INWEIGHT3].value,-5.0f,5.0f)*inputs[IN3].value;
	outputs[OUT].value = sum >= clamp(params[OUTFLOOR].value+inputs[INFLOOR].value,-10.0f,10.0f) ? 10.0f : 0.0f;
}

struct LabelDisplayWidget : TransparentWidget {
  float *value;
  std::shared_ptr<Font> font;

  LabelDisplayWidget() {
    font = APP->window->loadFont(asset::plugin(pluginInstance, "res/DejaVuSansMono.ttf"));
  };

  void draw(const DrawArgs &args) override
  {
    if (value) {
      char display[128];
  		snprintf(display, sizeof(display), "%2.2f", *value);
  		nvgFontSize(args.vg, 14.0f);
  		nvgFontFaceId(args.vg, font->handle);
  		nvgTextLetterSpacing(args.vg, -2.0f);
  		nvgFillColor(args.vg, YELLOW_BIDOO);
  		nvgTextAlign(args.vg, NVG_ALIGN_CENTER);
  		nvgRotate(args.vg,-1.0f * M_PI_2);
  		nvgText(args.vg, 0.0f, 0.0f, display, NULL);
    }
  }
};

struct LOURDEWidget : ModuleWidget {
	LOURDEWidget(LOURDE *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LOURDE.svg")));

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x-30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x-30, 365)));

  	addInput(createInput<PJ301MPort>(Vec(25.5,85), module, LOURDE::IN1));
    addInput(createInput<PJ301MPort>(Vec(25.5,155), module, LOURDE::IN2));
    addInput(createInput<PJ301MPort>(Vec(25.5,225), module, LOURDE::IN3));

    addInput(createInput<TinyPJ301MPort>(Vec(56.0f, 57.0f), module, LOURDE::INWEIGHT1));
    addInput(createInput<TinyPJ301MPort>(Vec(56.0f, 127.0f), module, LOURDE::INWEIGHT2));
    addInput(createInput<TinyPJ301MPort>(Vec(56.0f, 197.0f), module, LOURDE::INWEIGHT3));

    addParam(createParam<BidooBlueKnob>(Vec(22.5,50), module, LOURDE::WEIGHT1));
    addParam(createParam<BidooBlueKnob>(Vec(22.5,120), module, LOURDE::WEIGHT2));
    addParam(createParam<BidooBlueKnob>(Vec(22.5,190), module, LOURDE::WEIGHT3));

		LabelDisplayWidget *displayW1 = new LabelDisplayWidget();
		displayW1->box.pos = Vec(15,65);
		displayW1->value = module ? &module->params[LOURDE::WEIGHT1].value : NULL;
		addChild(displayW1);

		LabelDisplayWidget *displayW2 = new LabelDisplayWidget();
		displayW2->box.pos = Vec(15,135);
		displayW2->value = module ? &module->params[LOURDE::WEIGHT2].value : NULL;
		addChild(displayW2);

		LabelDisplayWidget *displayW3 = new LabelDisplayWidget();
		displayW3->box.pos = Vec(15,205);
		displayW3->value = module ? &module->params[LOURDE::WEIGHT3].value : NULL;
		addChild(displayW3);

    addParam(createParam<BidooBlueKnob>(Vec(22.5,270), module, LOURDE::OUTFLOOR));

		LabelDisplayWidget *displayOF = new LabelDisplayWidget();
		displayOF->box.pos = Vec(15,285);
		displayOF->value = module ? &module->params[LOURDE::OUTFLOOR].value : NULL;
		addChild(displayOF);

    addInput(createInput<TinyPJ301MPort>(Vec(56.0f, 277.0f), module, LOURDE::INFLOOR));

  	addOutput(createOutput<PJ301MPort>(Vec(25.5,320), module, LOURDE::OUT));
  }
};

Model *modelLOURDE = createModel<LOURDE, LOURDEWidget>("LoURdE");