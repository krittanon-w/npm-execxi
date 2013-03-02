all:
	node-gyp configure build
clean:
	rm -r build 
test:
	node test
gentest:
	node test| sed -e 's/nox/logan/g' | aha -b > test.html
	node test| sed -e 's/nox/logan/g' > test.log
