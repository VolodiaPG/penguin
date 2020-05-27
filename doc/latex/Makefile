SRC := README.md

all: output.pdf clean_build

build : output.pdf

o_abstract.tex: abstract.md
	pandoc abstract.md -o o_abstract.tex

output.pdf: o_abstract.tex references.bib $(SRC)
	pandoc $(SRC) -N -t latex --template=template.tex --natbib --highlight-style=monochrome \
	--variable style=exptech --variable links-as-notes --variable graphics --variable abstract=o_abstract.tex \
	-s -o output.tex
	pdflatex output
	bibtex output
	pdflatex output
	pdflatex output

.PHONY: clean clean_build

clean: clean_build
	$(RM) output.pdf

clean_build:
	$(RM) output.aux output.blg output.toc output.bbl output.tex *.log o_abstract.* *.aux *.fls *.fdb_latexmk

MKDIR_P ?= mkdir -p
