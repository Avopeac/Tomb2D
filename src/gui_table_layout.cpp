#include "gui_table_layout.h"

using namespace core;

GuiTableLayout::GuiTableLayout(size_t cells_x,
	size_t cells_y,
	const glm::vec2 &min_cell_size,
	const glm::vec2 &max_cell_size) :
	cells_x_(cells_x),
	cells_y_(cells_y),
	min_cell_size_(min_cell_size),
	max_cell_size_(max_cell_size)
{
}

void GuiTableLayout::Arrange(std::vector<std::shared_ptr<AbstractGuiElement>>& children,
	const glm::vec2 & parent_position, const glm::vec2 & parent_size)
{
	glm::vec2 cell_offset = parent_position;

	size_t cell_x = 0;
	size_t cell_y = 0;

	glm::vec2 min_cell_size_px = parent_size * min_cell_size_;
	glm::vec2 max_cell_size_px = parent_size * max_cell_size_;

	for (auto it = children.begin(); it != children.end(); ++it)
	{
		auto * element = (*it).get();

		glm::vec2 child_preferred_size = element->GetPreferredSize();

		auto h_align = element->GetHorizontalAlignmentProperty();
		auto v_align = element->GetVerticalAlignmentProperty();
		auto h_size = element->GetWidthProperty();
		auto v_size = element->GetHeightProperty();

		switch (h_align)
		{
			case GuiHorizontalAlignmentProperty::Left: {} break;
			case GuiHorizontalAlignmentProperty::Center: {} break;
			case GuiHorizontalAlignmentProperty::Right: {} break;
			default: break;
		}

		switch (v_align)
		{
			case GuiVerticalAlignmentProperty::Bottom: {} break;
			case GuiVerticalAlignmentProperty::Center: {} break;
			case GuiVerticalAlignmentProperty::Top: {} break;
			default: break;
		}

		element->SetArrangedPosition(cell_offset);
		element->SetArrangedSize(min_cell_size_px);
	}
}
