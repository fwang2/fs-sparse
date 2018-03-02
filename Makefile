all: sparse/_sparse.so

sparse/_sparse.so: sparse/*.py
	python $<

wheel:
	rm -rf dist
	python setup.py bdist_wheel

sdist:
	rm -rf dist
	python setup.py sdist

.PHONY: dist
dist:
	rm -rf dist/
	python setup.py sdist
	python setup.py bdist_wheel

clean:
	find . -name "*.pyc" -delete
	rm -rf pysparse.egg-info/
	rm -rf build/
	find . -name "*.so" -delete
