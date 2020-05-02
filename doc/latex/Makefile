BUILD_DIR ?= ./bin

SRC := README.md
ABSTRACT := abstract.md
BIB := references.bib

all: pdf

$(BUILD_DIR)/output.pdf: $(BUILD_DIR)/output.tex
	@$(MKDIR_P) $(dir $@)
	pdflatex -output-directory=$(BUILD_DIR) $(BUILD_DIR)/output.tex

$(BUILD_DIR)/abstract.tex: $(ABSTRACT)
	@$(MKDIR_P) $(dir $@)
	pandoc $(ABSTRACT) -o $@

$(BUILD_DIR)/output.tex: $(SRC) $(BUILD_DIR)/abstract.tex $(BIB)
	@$(MKDIR_P) $(dir $@)
	pandoc -N --template=template.tex $(SRC) --filter pandoc-fignos --variable abstract=$(BUILD_DIR)/abstract.tex --bibliography $(BIB) --toc -o $@

# tex: abstract.tex references.bib
# 	pandoc -N --template=template.tex README.md --bibliography references.bib --toc -o test.tex

tex: $(BUILD_DIR)/output.tex

pdf: $(BUILD_DIR)/output.pdf

clean:
	$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
