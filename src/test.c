#include <assert.h>

#define TEST

#include "main.c"

void testValidUrl() {
	assert(validUrl("http://github.com/owner/repo") == 1);
	assert(validUrl("https://github.com/owner/repo") == 1);
	assert(validUrl("https://github.com/owner/r") == 1);
	assert(validUrl("https://github.com/o/repo") == 1);
	assert(validUrl("https://github.com/o/r") == 1);
	assert(validUrl("https://github.com/1/r") == 1);
	assert(validUrl("https://github.com/abc/123") == 1);
	assert(validUrl("https://github.com/123/abc") == 1);
	assert(validUrl("https://github.com/owner/with_underscore") == 1);
	assert(validUrl("https://github.com/ow_ner/repo") == 1);
	assert(validUrl("https://github.com/ow_ner/repo_") == 1);

	assert(validUrl("http://github.com/owner/") == 0);
	assert(validUrl("http://github.com/o/") == 0);
	assert(validUrl("http://github.com//repo") == 0);
	assert(validUrl("http://github.com//r") == 0);
	assert(validUrl("http://github.com//") == 0);
	assert(validUrl("http://github/owner/repo") == 0);
	assert(validUrl("http://site/owner/repo") == 0);
	assert(validUrl("http:/github.com/owner/repo") == 0);
	assert(validUrl("http:github.com/owner/repo") == 0);
	assert(validUrl("httpgithub.com/owner/repo") == 0);
	assert(validUrl("github.com/owner/repo") == 0);
	assert(validUrl("htt://github.com/owner/repo") == 0);
	assert(validUrl("://github.com/owner/repo") == 0);
	assert(validUrl("https://github.com/singleword") == 0);
	assert(validUrl("https://github.com/ow;/repo") == 0);
	assert(validUrl("https://github.com/ow/repo;") == 0);
	assert(validUrl("https://github.com/ow/re;po") == 0);
	assert(validUrl("https://github.com/o;w/repo") == 0);
	assert(validUrl("https://github.com/owner/repo/") == 0);
	assert(validUrl("https://github.com/owner/re/po") == 0);
}

int main() {
	testValidUrl();
	return 0;
}

