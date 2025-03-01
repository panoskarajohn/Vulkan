CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
VULKAN_SDK_PATH = /Users/panagiotiskaragiannis/VulkanSDK/1.4.304.1
INCLUDE_DIRS = -I$(VULKAN_SDK_PATH)/macOS/include
LIBRARY_DIRS = -L$(VULKAN_SDK_PATH)/macOS/lib
LIBS = -lvulkan

TARGET = vulkan_test
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBRARY_DIRS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)