ASCIIDOCTOR_PDF = asciidoctor-pdf
SOURCE = book.adoc
BUILD_DIR = build

.PHONY: all publish clean

all: publish

publish:
	@echo "Generating PDF..."
	@mkdir -p $(BUILD_DIR)
	$(ASCIIDOCTOR_PDF) $(SOURCE) -o $(BUILD_DIR)/manual-handbook.pdf
	@echo "PDF created in $(BUILD_DIR)/"

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)