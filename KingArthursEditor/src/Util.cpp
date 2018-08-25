#include "Util.hpp"

const char *Util::KeyToString(sf::Keyboard::Key key) {
	
	#define MAP_KEY(_key_) case sf::Keyboard::_key_: return #_key_;

	switch (key) {
		MAP_KEY(Unknown);
		MAP_KEY(A);
		MAP_KEY(B);
		MAP_KEY(C);
		MAP_KEY(D);
		MAP_KEY(E);
		MAP_KEY(F);
		MAP_KEY(G);
		MAP_KEY(H);
		MAP_KEY(I);
		MAP_KEY(J);
		MAP_KEY(K);
		MAP_KEY(L);
		MAP_KEY(M);
		MAP_KEY(N);
		MAP_KEY(O);
		MAP_KEY(P);
		MAP_KEY(Q);
		MAP_KEY(R);
		MAP_KEY(S);
		MAP_KEY(T);
		MAP_KEY(U);
		MAP_KEY(V);
		MAP_KEY(W);
		MAP_KEY(X);
		MAP_KEY(Y);
		MAP_KEY(Z);
		MAP_KEY(Num0);
		MAP_KEY(Num1);
		MAP_KEY(Num2);
		MAP_KEY(Num3);
		MAP_KEY(Num4);
		MAP_KEY(Num5);
		MAP_KEY(Num6);
		MAP_KEY(Num7);
		MAP_KEY(Num8);
		MAP_KEY(Num9);
		MAP_KEY(Numpad0);
		MAP_KEY(Numpad1);
		MAP_KEY(Numpad2);
		MAP_KEY(Numpad3);
		MAP_KEY(Numpad4);
		MAP_KEY(Numpad5);
		MAP_KEY(Numpad6);
		MAP_KEY(Numpad7);
		MAP_KEY(Numpad8);
		MAP_KEY(Numpad9);
		MAP_KEY(Escape);
		MAP_KEY(LControl);
		MAP_KEY(RControl);
		MAP_KEY(LShift);
		MAP_KEY(RShift);
		MAP_KEY(LAlt);
		MAP_KEY(RAlt);
		MAP_KEY(LSystem);
		MAP_KEY(RSystem);
		MAP_KEY(Menu);
		MAP_KEY(LBracket);
		MAP_KEY(RBracket);
		MAP_KEY(SemiColon);
		MAP_KEY(Comma);
		MAP_KEY(Period);
		MAP_KEY(Quote);
		MAP_KEY(Slash);
		MAP_KEY(BackSlash);
		MAP_KEY(Tilde);
		MAP_KEY(Equal);
		MAP_KEY(Dash);
		MAP_KEY(Space);
		MAP_KEY(Return);
		MAP_KEY(BackSpace);
		MAP_KEY(Tab);
		MAP_KEY(PageUp);
		MAP_KEY(PageDown);
		MAP_KEY(End);
		MAP_KEY(Home);
		MAP_KEY(Insert);
		MAP_KEY(Delete);
		MAP_KEY(Add);
		MAP_KEY(Subtract);
		MAP_KEY(Multiply);
		MAP_KEY(Divide);
		MAP_KEY(Left);
		MAP_KEY(Right);
		MAP_KEY(Up);
		MAP_KEY(Down);
		MAP_KEY(F1);
		MAP_KEY(F2);
		MAP_KEY(F3);
		MAP_KEY(F4);
		MAP_KEY(F5);
		MAP_KEY(F6);
		MAP_KEY(F7);
		MAP_KEY(F8);
		MAP_KEY(F9);
		MAP_KEY(F10);
		MAP_KEY(F11);
		MAP_KEY(F12);
		MAP_KEY(F13);
		MAP_KEY(F14);
		MAP_KEY(F15);
		MAP_KEY(Pause);

		default: break;
	};

	#undef MAP_KEY

	return "<not found>";
}

sf::Keyboard::Key Util::StringToKey(const char *name) {
	
	#define MAP_KEY(key) if (strcmp(name, #key) == 0) return sf::Keyboard::key;

	MAP_KEY(Unknown) else
	MAP_KEY(A) else
	MAP_KEY(B) else
	MAP_KEY(C) else
	MAP_KEY(D) else
	MAP_KEY(E) else
	MAP_KEY(F) else
	MAP_KEY(G) else
	MAP_KEY(H) else
	MAP_KEY(I) else
	MAP_KEY(J) else
	MAP_KEY(K) else
	MAP_KEY(L) else
	MAP_KEY(M) else
	MAP_KEY(N) else
	MAP_KEY(O) else
	MAP_KEY(P) else
	MAP_KEY(Q) else
	MAP_KEY(R) else
	MAP_KEY(S) else
	MAP_KEY(T) else
	MAP_KEY(U) else
	MAP_KEY(V) else
	MAP_KEY(W) else
	MAP_KEY(X) else
	MAP_KEY(Y) else
	MAP_KEY(Z) else
	MAP_KEY(Num0) else
	MAP_KEY(Num1) else
	MAP_KEY(Num2) else
	MAP_KEY(Num3) else
	MAP_KEY(Num4) else
	MAP_KEY(Num5) else
	MAP_KEY(Num6) else
	MAP_KEY(Num7) else
	MAP_KEY(Num8) else
	MAP_KEY(Num9) else
	MAP_KEY(Numpad0) else
	MAP_KEY(Numpad1) else
	MAP_KEY(Numpad2) else
	MAP_KEY(Numpad3) else
	MAP_KEY(Numpad4) else
	MAP_KEY(Numpad5) else
	MAP_KEY(Numpad6) else
	MAP_KEY(Numpad7) else
	MAP_KEY(Numpad8) else
	MAP_KEY(Numpad9) else
	MAP_KEY(Escape) else
	MAP_KEY(LControl) else
	MAP_KEY(RControl) else
	MAP_KEY(LShift) else
	MAP_KEY(RShift) else
	MAP_KEY(LAlt) else
	MAP_KEY(RAlt) else
	MAP_KEY(LSystem) else
	MAP_KEY(RSystem) else
	MAP_KEY(Menu) else
	MAP_KEY(LBracket) else
	MAP_KEY(RBracket) else
	MAP_KEY(SemiColon) else
	MAP_KEY(Comma) else
	MAP_KEY(Period) else
	MAP_KEY(Quote) else
	MAP_KEY(Slash) else
	MAP_KEY(BackSlash) else
	MAP_KEY(Tilde) else
	MAP_KEY(Equal) else
	MAP_KEY(Dash) else
	MAP_KEY(Space) else
	MAP_KEY(Return) else
	MAP_KEY(BackSpace) else
	MAP_KEY(Tab) else
	MAP_KEY(PageUp) else
	MAP_KEY(PageDown) else
	MAP_KEY(End) else
	MAP_KEY(Home) else
	MAP_KEY(Insert) else
	MAP_KEY(Delete) else
	MAP_KEY(Add) else
	MAP_KEY(Subtract) else
	MAP_KEY(Multiply) else
	MAP_KEY(Divide) else
	MAP_KEY(Left) else
	MAP_KEY(Right) else
	MAP_KEY(Up) else
	MAP_KEY(Down) else
	MAP_KEY(F1) else
	MAP_KEY(F2) else
	MAP_KEY(F3) else
	MAP_KEY(F4) else
	MAP_KEY(F5) else
	MAP_KEY(F6) else
	MAP_KEY(F7) else
	MAP_KEY(F8) else
	MAP_KEY(F9) else
	MAP_KEY(F10) else
	MAP_KEY(F11) else
	MAP_KEY(F12) else
	MAP_KEY(F13) else
	MAP_KEY(F14) else
	MAP_KEY(F15) else
	MAP_KEY(Pause)

	#undef MAP_KEY

	return sf::Keyboard::Unknown;
}

