#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "edge.h"
#include "triplet.h"


void testTriplet(const char* src, const char* relationship, const char* dest, TripletKind expectedKind, const char* expectedStrRepresentation) {
	Node* srcNode = NewNode(src);
	Node* destNode = NewNode(dest);
	Edge* edge = NewEdge(srcNode, destNode, relationship);

	Triplet* triplet = BuildTriplet(edge);

	FreeEdge(edge);
	FreeNode(srcNode);
	FreeNode(destNode);

	assert(strcmp(triplet->subject, src) == 0);
	assert(strcmp(triplet->predicate, relationship) == 0);
	assert(strcmp(triplet->object, dest) == 0);
	assert(triplet->kind == expectedKind);

	char* str = TripletToString(triplet);
	if(str == 0) {
		assert(str == expectedStrRepresentation);
	} else {
		assert(strcmp(str, expectedStrRepresentation) == 0);
	}
	
	FreeTriplet(triplet);
}

int main(int argc, char **argv) {
	testTriplet("", "", "", UNKNOW, 0);
	testTriplet("me", "", "", S, "SPO:me:");
	testTriplet("", "", "Tokyo", O, "OPS:Tokyo:");
	testTriplet("", "friend with", "", P, "POS:friend with:");
	testTriplet("me", "friend with", "", SP, "SPO:me:friend with:");	
	testTriplet("", "visit", "Tokyo", PO, "POS:visit:Tokyo:");
	testTriplet("me", "", "beer", SO, "SOP:me:beer:");
	testTriplet("me", "love", "beer", SPO, "SPO:me:love:beer");
	
	printf("PASS!");
    return 0;
}