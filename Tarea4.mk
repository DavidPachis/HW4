plots = cuerdaFija.pdf CuerdaFijaConPertur.pdf

Resultados_hw4.pdf :Resultados_hw4.tex $(plots)
	pdflatex
Resultados_hw4.tex $(plots): .txt
	python Plots.py
.txt: a.out
	./a.out
a.out: Ondas.c
	cc Ondas.c -lm
