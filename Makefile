all: sparse/_sparse.so

sparse/_sparse.so: sparse/*.py
	python $<

clean:
	find . -name "*.pyc" -delete
	rm -rf pysparse.egg-info/
	rm -rf build/
	find . -name "*.so" -delete
