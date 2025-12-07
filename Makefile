CXX = g++
# CXXFLAGS: Removed -pthread
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = build/gitlite
# Exclude thread_pool.cpp from source list if you haven't deleted the file yet
SRC = src/main.cpp src/buffer_manager.cpp src/commit.cpp src/diff.cpp src/filesystem.cpp src/hashing.cpp src/ipc_handler.cpp src/proess_manager.cpp

all:
	@echo "📦 Starting GitLite Build (Sequential)..."
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