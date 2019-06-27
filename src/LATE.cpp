#include "plugin.hpp"
#include "BidooComponents.hpp"
#include "dsp/digital.hpp"
#include <ctime>

using namespace std;

struct LATE : Module {
	enum ParamIds {
		SWING_PARAM,
		CVCOEFF_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SWING_INPUT,
		CLOCK_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		CLOCK_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	bool odd = true;
	bool armed = false;
	dsp::SchmittTrigger clockTrigger;
	dsp::SchmittTrigger resetTrigger;
	clock_t tCurrent = clock();
	clock_t tPrevious = clock();


	LATE() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(SWING_PARAM, 0, 9, 0, "Swing");
		configParam(CVCOEFF_PARAM, -1.0f, 1.0f, 0.0f, "Placeholder");
	}

	void process(const ProcessArgs &args) override {
		outputs[CLOCK_OUTPUT].setVoltage(0.f);
		clock_t now = clock();

		if (resetTrigger.process(inputs[RESET_INPUT].getVoltage())) {
			odd = true;
		}

		if (clockTrigger.process(inputs[CLOCK_INPUT].getVoltage())) {
			tPrevious = tCurrent;
			tCurrent = now;
			if (odd) {
				outputs[CLOCK_OUTPUT].setVoltage(10.0f);
				odd = false;
				armed = false;
			} else {
				armed = true;
			}
		}

		float lag = rescale(clamp(params[SWING_PARAM].getValue() + params[CVCOEFF_PARAM].getValue() * inputs[SWING_INPUT].getVoltage(), 0.0f, 9.0f), 0.0f, 10.0f, 0.0f, (float)tCurrent - (float)tPrevious);

		if (armed && !odd && (((float)now - (float)tCurrent) >= lag)) {
			outputs[CLOCK_OUTPUT].setVoltage(10.0f);
			armed = false;
			odd = true;
		}
	}

};

struct LATEWidget : ModuleWidget {
	LATEWidget(LATE *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LATE.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		
		addParam(createParam<BidooBlueKnob>(Vec(8, 70), module, LATE::SWING_PARAM));
		addParam(createParam<BidooBlueTrimpot>(Vec(13, 105), module, LATE::CVCOEFF_PARAM));

		addInput(createInput<PJ301MPort>(Vec(10, 130), module, LATE::SWING_INPUT));
		addInput(createInput<PJ301MPort>(Vec(10, 186.33f), module, LATE::RESET_INPUT));
		addInput(createInput<PJ301MPort>(Vec(10, 242.66f), module, LATE::CLOCK_INPUT));

		addOutput(createOutput<PJ301MPort>(Vec(10, 299), module, LATE::CLOCK_OUTPUT));
	}
};

Model *modelLATE = createModel<LATE, LATEWidget>("lATe");
