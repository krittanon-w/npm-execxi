all:
	node-gyp configure build
clean:
	rm -r build 
test:
	node test
# gentest:
# 	node test| sed -e 's/logan2/logan/g' | aha -b > test.html
# 	node test| sed -e 's/logan2/logan/g' > test.log
