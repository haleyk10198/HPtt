//return gcd = fst*a + snd*b

pii egcd(ll a, ll b){
	if(a > b){
		pii ret = egcd(b, a);
		return mp(ret.second, ret.first);
	}
	if(a == 0) return mp(0, 1);
	pii p = egcd(b%a, a);
	return mp(p.second - (b/a)*p.first, p.first);
}

/* Solving CRT:
ai = mi mod pi

S = p1 * p2 * p3 ..... * pn
find 
ri = 1 mod pi, ri = 0 mod S/pi 
with
1 = x*pi + y * S/pi
ri = 1 - x*pi = y * S/pi by egcd

solution = sum(ri*ai) */
