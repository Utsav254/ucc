#pragma once
struct YYLTYPE {
	int first_column;
	int last_column;
	int first_line;
	int last_line;

	YYLTYPE() : first_column(1) , last_column(1) , first_line(1) , last_line(1) {}
	YYLTYPE(int fc , int lc , int fl , int ll) : first_column(fc) , last_column(lc) , first_line(fl) , last_line(ll) {}

};
