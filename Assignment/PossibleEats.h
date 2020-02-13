#pragma once

class PossibleEats {
	public:
		PossibleEats(bool tl, bool tr, bool bl, bool br) : top_left(tl), top_right(tr), bottom_left(bl), bottom_right(br) {}

		bool top_left;
		bool top_right;
		bool bottom_left;
		bool bottom_right;
};