#include "includes.h"

std::string comp_name1()
{

	char buff[MAX_PATH];
	GetEnvironmentVariableA("USERNAME", buff, MAX_PATH);

	return std::string(buff);
};

void Form::draw() {
	// opacity should reach 1 in 500 milliseconds.
	constexpr float frequency = 2.f / 0.5f;

	// the increment / decrement per frame.
	float step = frequency * g_csgo.m_globals->m_frametime;

	// if open		-> increment
	// if closed	-> decrement
	m_open ? m_opacity += step : m_opacity -= step;

	// clamp the opacity.
	math::clamp(m_opacity, 0.f, 1.f);

	m_alpha = 0xff * m_opacity;
	if (!m_alpha)
		return;

	// get gui color.
	Color color = g_gui.m_color;
	color.a() = m_alpha;

	// background.
	render::rect_filled(m_x, m_y, m_width, m_height, { 15, 15, 15, m_alpha });
	Color gui_color = g_menu.main.config.menu_color.get();

	render::rect_filled(m_x, m_y + 482, m_width, 17, { 43, 43, 43, 150 });

	render::menu.string(m_x + 5, m_y + 484, { color }, "za", render::ALIGN_LEFT);

	std::string text = tfm::format(XOR("pta [early] | %s"), comp_name1());
	render::FontSize_t size = render::menu.size(text);
	render::menu.string(m_x + 18, m_y + 484, { 186, 186, 186, m_alpha }, text, render::ALIGN_LEFT);


	// border.
	render::rect(m_x, m_y, m_width, m_height, { 43, 43, 43, m_alpha });
	render::rect_filled(m_x, m_y + 38, m_width, 2, { 43, 43, 43, 150 });
	//render

	// draw tabs if we have any.
	if (!m_tabs.empty()) {
		Rect tabs_area = GetTabsRect();

		for (size_t i{}; i < m_tabs.size(); ++i) {
			const auto& t = m_tabs[i];
			int font_width = render::menu_shade.size(t->m_title).m_width;

			Color def_col = Color{ 152, 152, 152 };

			// text
			render::menu_shade.string(tabs_area.x + (i * (tabs_area.w / m_tabs.size())) + 16, tabs_area.y - 7,
				t == m_active_tab ? color : def_col, t->m_title);


			int fx = m_x + 138;
			int next_group = (fx + 5) + (450 / 2) - 3;

			for (size_t i{}; i < m_tabs.size(); ++i) {
				const auto& t = m_tabs[i];

				if (t == m_active_tab) {

					render::menu.string(fx + 6, m_y + 35, palette::accent_2.alpha(70), t->m_group_name_1);
					render::menu.string(next_group + 8, m_y + 35, palette::accent_2.alpha(70), t->m_group_name_2);
				}
			}
			// active tab indicator

			//render::rect_filled_fade(tabs_area.x + (i * (tabs_area.w / m_tabs.size())) + 10, tabs_area.y + 7,
				//font_width + 11, 2,
				//t == m_active_tab ? Color{ 0, 0, 0, 0 } : Color{ 0, 0, 0, m_alpha }, 0, 150);

			//render::rect_filled(tabs_area.x + (i * (tabs_area.w / m_tabs.size())) + 10, tabs_area.y + 7,
				//font_width + 11, 2,
				//t == m_active_tab ? color : Color{ 0, 0, 0, 0 });

			//render::rect_filled(m_x, tabs_area.y + 7, m_x ,2, Color{ 255, 255, 255, 255 });
		}

		// this tab has elements.
		if (!m_active_tab->m_elements.empty()) {
			// elements background and border.
			Rect el = GetElementsRect();



			// iterate elements to display.
			for (const auto& e : m_active_tab->m_elements) {

				// draw the active element last.
				if (!e || (m_active_element && e == m_active_element))
					continue;

				if (!e->m_show)
					continue;

				// this element we dont draw.
				if (!(e->m_flags & ElementFlags::DRAW))
					continue;

				e->draw();
			}

			// we still have to draw one last fucker.
			if (m_active_element && m_active_element->m_show)
				m_active_element->draw();
		}
	}
}