#pragma once

#include "abstract_gui_layout.h"

namespace core {

	class GuiTableLayout : public AbstractGuiLayout
	{

		size_t cells_x_; 
		size_t cells_y_;
		glm::vec2 min_cell_size_;
		glm::vec2 max_cell_size_;

	public:

		GuiTableLayout(size_t cells_x,
			size_t cells_y,
			const glm::vec2 &min_cell_size,
			const glm::vec2 &max_cell_size);

		~GuiTableLayout() = default;

		virtual void Arrange(std::vector<std::shared_ptr<AbstractGuiElement>>& children, 
			const glm::vec2 & parent_position, const glm::vec2 & parent_size) override;

	};
}
