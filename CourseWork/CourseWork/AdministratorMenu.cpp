#include "TableManips.h"

extern void AdminFunctionsMenu() {
	const string OPTIONS_TO_CHOOSE[5] = { "Çàñïàâíèòü íîâûõ ó÷åíèêîâ","Ïîøåë íàõóé","Õóé ïèñÿ ïîïà", "×ëååí","õç"};
	const string HEADER = { "ÌÅÍÞ ÀÄÌÈÍÈÑÒÐÀÒÎÐÀ" };

	PrintMenuWithOptionsHeaderCentralized(5, OPTIONS_TO_CHOOSE, HEADER);

	int n;
	cin >> n;
}