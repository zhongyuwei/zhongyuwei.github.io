//KrK

#pragma comment(linker, "/STACK:16000000")
using namespace std;
 
const int Maxn = 100005;
 
char str[Maxn];
string S, T;
int Z[Maxn];
vector <int> seq;
 
void Read(string &s)
{
	scanf("%s", str); s = str;
}
 
bool Check(int a)
{
	if (a + T.length() > S.length()) return false;
	for (int i = 0; i < T.length(); i++)
		if (S[a + i] != '?' && S[a + i] != T[i]) return false;
	return true;
}
 
int Solve(int pos);
 
int Solved(int pos)
{
	for (int i = 0; i < seq.size(); i++)
		if (Check(pos + seq[i])) return 1 + Solved(pos + seq[i]);
	return Solve(pos + T.length());
}
 
int Solve(int pos)
{
	if (pos >= S.length()) return 0;
	if (Check(pos)) return 1 + Solved(pos);
	return Solve(pos + 1);
}
 
int main()
{
	Read(S);
	Read(T);
	int l = -1, r = -1;
	for (int i = 1; i < T.length(); i++) {
		if (i <= r) Z[i] = min(Z[i - l], r - i);
		while (i + Z[i] < T.length() && T[Z[i]] == T[i + Z[i]]) Z[i]++;
		if (i + Z[i] - 1 > r) {
			r = i + Z[i] - 1; l = i;
		}
		if (i + Z[i] >= T.length()) seq.push_back(i);
	}
	printf("%d\n", Solve(0));
	return 0;
}
