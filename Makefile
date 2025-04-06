CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
VULKAN_SDK_PATH = /Users/panagiotiskaragiannis/VulkanSDK/1.4.304.1

# Include and library directories
INCLUDE_DIRS = -I$(VULKAN_SDK_PATH)/macOS/include $(foreach dir, $(wildcard */), -I$(dir))
LIBRARY_DIRS = -L$(VULKAN_SDK_PATH)/macOS/lib
LIBS = -lvulkan

# Target and source files
TARGET = output/vulkan_test
SOURCES = main.cpp $(wildcard */*.cpp)
OBJECTS = $(patsubst %.cpp, output/%.o, $(SOURCES))

# Default target
all: $(TARGET)

# Linking the target
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LIBRARY_DIRS) -o $@ $^ $(LIBS)

# Compiling object files
output/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Cleaning up
clean:
	rm -rf output