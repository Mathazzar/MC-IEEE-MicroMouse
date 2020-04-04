#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char Q3[] = "1a2a3a4a5a6a7a8a17a18a19a20a21a22a23a24a33a34a35a36a37a38a39a40a49a50a51a52a53a54a55a56a65a66a67a68a69a70a71a72a81a82a83a84a85a86a87a88a97a98a99a100a101a102a103a104";
char Q4[] = "9a10a11a12a13a14a15a16a25a26a27a28a29a30a31a32a41a42a43a44a45a46a47a48a57a58a59a60a61a62a63a64a73a74a75a76a77a78a79a80a89a90a91a92a93a94a95a96a105a106a107a108a109a110a111a112a";
char Q2[] = "129a130a131a132a133a134a135a145a146a147a148a149a150a151a152a161a162a163a164a165a166a167a168a177a178a179a180a181a182a183a184a193a194a195a196a197a198a199a200a209a210a211a212a213a214a215a216a225a226a227a228a229a230a231a232a241a242a243a244a245a246a247a248a";
char Q1[] = "138a139a140a141a142a143a144a153a154a155a156a157a158a159a160a169a170a171a172a173a174a175a176a185a186a187a188a189a190a191a192a201a202a203a204a205a206a207a208a217a218a219a220a221a222a223a224a233a234a235a236a237a238a239a240a249a250a251a252a253a254a255a256a";

/*Heuristic*/
int calculate_heuristic_distance(int NIN)
{
	char NINstr[5];
	snprintf(NINstr, 5, "%da", NIN);
	//itoa(NIN, NINstr, 5);
	int distanceToGoal = 0;
	int goal;
	//strcat(NINstr, "a");

	if (strcmp(NINstr, Q3))
	{
		goal = 120 - NIN;
		while (goal >= 16)
		{
			distanceToGoal++;
			goal -= 16;
		}
		while (goal > 0)
		{
			distanceToGoal++;
			goal--;
		}
		return distanceToGoal;
	}
	else if (strcmp(NINstr, Q4))
	{
		goal = 121 - NIN;
		while (goal > 0)
		{
			distanceToGoal++;
			goal -= 16;
		}
		while (goal < 0)
		{
			distanceToGoal++;
			goal++;
		}
		return distanceToGoal;
	}
	else if (strcmp(NINstr, Q2))
	{
		goal = 136 - NIN;
		while (goal <= -16 || goal < 0)
		{
			distanceToGoal++;
			goal += 16;
		}
		while (goal > 0)
		{
			distanceToGoal++;
			goal--;
		}
		return distanceToGoal;
	}
	else if (strcmp(NINstr, Q1))
	{
		goal = 137 - NIN;
		while (goal <= -16)
		{
			distanceToGoal++;
			goal += 16;
		}
		while (goal < 0)
		{
			distanceToGoal++;
			goal++;
		}
		return distanceToGoal;
	}
}//end heuristic distance