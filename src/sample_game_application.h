#pragma once

#include "application.h"

#include "map_data.h"
#include "map_parser.h"
#include "map_view.h"

namespace game {

	class SampleGameApplication : public core::Application
	{

		std::unique_ptr<MapData> map_data_ = nullptr;
		std::unique_ptr<MapParser> map_parser_ = nullptr;
		std::unique_ptr<MapView> map_view_ = nullptr;

		core::AudioSource * background_music_ = nullptr;

	public:

		SampleGameApplication() = default;

		~SampleGameApplication() = default;

		// Inherited via Application
		virtual bool Run(const core::SystemPtrs &, const core::Config &, float) override;

		virtual bool StartUp(const core::SystemPtrs &, const core::Config &) override;

		virtual bool CleanUp(const core::SystemPtrs &) override;
	};
}
