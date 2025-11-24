CXX = g++
# CXXFLAGS: Fixed -02 to the correct optimization flag -O2
CXXFLAGS = -std=c++17 -Wall -pthread -O2
TARGET = build/gitlite
SRC = src/*.cpp

all:
	@echo "📦 Starting GitLite Build..."
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	@echo "✅ Build complete: $(TARGET)"

clean:
	rm -rf build/
	rm -rf .gitlite/
	@echo "🗑️  Cleaned build files and .gitlite repository"

run:
	@echo "🚀 Running initialization test..."
	./gitlite.sh init

test:
	@echo "🧪 Running complex test sequence..."
	./tests/run_tests.sh
