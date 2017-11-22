#pragma once

#include <functional>

#include "glm/glm.hpp"

namespace graphics {

	using PropagateInteraction = bool;

	using Interaction = std::function<PropagateInteraction(const glm::ivec2 &)>;

	class AbstractGuiElement
	{

		static size_t uid_counter_;

		size_t uid_;

		glm::ivec2 padding_;

		glm::ivec2 margin_;

		glm::ivec2 preferred_size_;

		glm::ivec2 bounds_;

		Interaction hit_event_;

		Interaction hover_event_;

		Interaction dehover_event_;

	public:

		AbstractGuiElement();

		~AbstractGuiElement();

		AbstractGuiElement(const AbstractGuiElement &) = delete;

		AbstractGuiElement(AbstractGuiElement &&) = delete;

		AbstractGuiElement& operator=(const AbstractGuiElement &) = delete;

		AbstractGuiElement& operator=(AbstractGuiElement &&) = delete;

		inline size_t GetUniqueId() const
		{
			return uid_;
		}

		inline const Interaction &GetHitEvent() const
		{
			return hit_event_;
		}

		inline const Interaction &GetHoverEvent() const
		{
			return hover_event_;
		}

		inline const Interaction &GetDehoverEvent() const
		{
			return dehover_event_;
		}

		inline void SetHitEvent(const Interaction &hit_event)
		{
			hit_event_ = hit_event;
		}

		inline void SetHoverEvent(const Interaction &hover_event)
		{
			hover_event_ = hover_event;
		}

		inline void SetDehoverEvent(const Interaction &dehover_event)
		{
			dehover_event_ = dehover_event;
		}
	};
}
