#pragma once

#include <string>
#include <glm/glm.hpp>

#include "component.h"

namespace game
{
	class SpriteAnimationComponent : public core::Component
	{

		bool dirty_ = true;

		std::string texture_path_;

		size_t texture_hash_;

		int32_t frames_per_second_;
		int32_t num_row_frames_;
		int32_t num_column_frames_;
		int32_t start_frame_;
		int32_t end_frame_;
		int32_t current_frame_;

		float elapsed_time_ = 0.0f;
		
	public:

		SpriteAnimationComponent(const std::string &texture_path,
			int32_t frames_per_second, 
			int32_t num_row_frames,
			int32_t num_column_frames, 
			int32_t start_frame, 
			int32_t end_frame) :
			texture_path_(texture_path),
			frames_per_second_(frames_per_second),
			num_row_frames_(num_row_frames),
			num_column_frames_(num_column_frames),
			start_frame_(start_frame),
			end_frame_(end_frame),
			current_frame_(start_frame)
		{
		}

		virtual ~SpriteAnimationComponent() {}

		inline bool IsDirty() const { return dirty_; }

		inline void LowerDirty() { dirty_ = false; }

		inline const std::string &GetTexturePath() const { return texture_path_; }

		inline void SetTexturePath(const std::string &path) 
		{
			dirty_ = true; 
			texture_path_ = path;
		}

		inline int32_t GetFramesPerSecond() const { return frames_per_second_; }

		inline void SetFramesPerSeconds(int32_t frames_per_second) { frames_per_second_ = frames_per_second; }

		inline int32_t GetNumRowFrames() const { return num_row_frames_; }

		inline void SetNumRowFrames(int32_t num_row_frames) { num_row_frames_ = num_row_frames; }

		inline int32_t GetNumColumnFrames() const { return num_column_frames_; }

		inline void SetNumColumnFrames(int32_t num_column_frames) { num_column_frames_ = num_column_frames; }

		inline int32_t GetStartFrame() const { return start_frame_; }

		inline void SetStartFrame(int32_t start_frame) { start_frame_ = start_frame; }

		inline int32_t GetEndFrame() const { return end_frame_; }

		inline void SetEndFrame(int32_t end_frame) { end_frame_ = end_frame; }

		inline void SetCurrentFrame(int32_t current_frame) { current_frame_ = current_frame; }

		inline int32_t GetCurrentFrame() const { return current_frame_; }

		inline void SetElapsedTime(float elapsed_time) { elapsed_time_ = elapsed_time; }

		inline float GetElapsedTime() const { return elapsed_time_; }

		inline void SetTextureHash(size_t hash) { texture_hash_ = hash; }

		inline size_t GetTextureHash() const { return texture_hash_; }
	};
}
