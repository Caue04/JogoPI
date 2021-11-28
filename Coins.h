claas Coin {
	private:
		int aWx, delay, t;
		
	public:
		int wx, wy, x, y, h, aDir;
		Coin(int _wx, int _wy, int _x, int _y, int _w, int _h, int _aDir) {
			t = 0;
			x = _x;
			y = _y;
			w = _w;
			h = _h;	
			wx = _wx;
			wy = _wy;
			aWx = _wx;
			delay = 0;
			aDir = _aDir;
		}
		
		void show(BITMAP *buffer, BITMAP *iSource) {
			masked_blit(iSource, buffer, wx, wy, x, y, w, h);	
		}	
};
