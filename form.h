#pragma once

namespace palette {
	inline auto backround = Color(13, 13, 13);
	inline auto backround2 = Color(8, 8, 8);
	inline auto outline_1 = Color(5, 5, 5);
	inline auto outline_2 = Color(26, 26, 26);
	inline auto accent = Color(165, 108, 245);
	inline auto accent_2 = Color(220, 220, 220, 40);
	inline auto elements_outline = Color(5, 5, 5);
}

class Form {
	friend class GUI;
	friend class Element;
	friend class Dropdown;
	friend class MultiDropdown;
	friend class Colorpicker;
	friend class Edit;
	friend class Config;

public:
	bool                m_open;
	float               m_opacity;
	int                 m_alpha;
private:
	int                 m_key;
	int	                m_x;
	int	                m_y;
	int                 m_width;
	int                 m_height;
	int                 m_tick;
	std::vector< Tab* >	m_tabs;
	Tab* m_active_tab;
	Element* m_active_element;

public:
	__forceinline Form() : m_open{ true }, m_opacity{}, m_alpha{}, m_key{ -1 }, m_x{}, m_y{}, m_width{}, m_height{}, m_tick{}, m_tabs{}, m_active_tab{}, m_active_element{} {}

	__forceinline void SetPosition(int x, int y) {
		m_x = x;
		m_y = y;
	}

	__forceinline void SetSize(int w, int h) {
		m_width = w;
		m_height = h - 70;
	}

	__forceinline void SetToggle(int key) {
		m_key = key;
	}

	// adds a new tab.
	__forceinline void RegisterTab(Tab* tab) {
		// if this is the first tab, set the active tab.
		if (!m_tabs.size())
			m_active_tab = tab;

		// this form is the owner of the tab.
		tab->m_parent = this;

		// add the tab to our container.
		m_tabs.push_back(tab);
	}

	// get specific tab based off name.
	__forceinline Tab* GetTabByName(const std::string& name) const {
		auto it = std::find_if(m_tabs.begin(), m_tabs.end(),
			[&name](Tab* tab) {
				return !tab->m_title.compare(name);
			});

		if (it != m_tabs.end())
			return *it;

		return nullptr;
	}

	// toggles the form.
	__forceinline void toggle() {
		m_open = !m_open;
	}

	// get the click-able area.
	__forceinline Rect GetClientRect() const {
		return { m_x + 6, m_y + 6, m_width - 12, m_height - 12 };
	}

	__forceinline Rect GetFormRect() const {
		return { m_x, m_y, m_width, m_height };
	}

	__forceinline Rect GetTabsRect() const {
		return { m_x + 20, m_y + 25, m_width - 40, 20 };
	}

	__forceinline Rect GetElementsRect() const {
		Rect tabs_area = GetTabsRect();
		return { tabs_area.x, tabs_area.y + tabs_area.h + 6, tabs_area.w, m_height - tabs_area.h - 46 };
	}

public:
	void draw();
};