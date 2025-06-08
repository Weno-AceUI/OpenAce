#include "test_framework.h"
#include "../../kernel/services/devmgr.h"
#include "../../kernel/drivers/driver.h"

// Test case for device registration
TEST_CASE(test_device_registration) {
    // Initialize the device manager
    devmgr_init();
    
    // Register a device type
    bool type_result = devmgr_register_type("test_type", "Test device type");
    ASSERT(type_result, "Device type registration failed");
    
    // Register a device
    uint64_t device_id = devmgr_register_device("test_device", DEVICE_TYPE_DISK, 1);
    ASSERT(device_id != 0, "Device registration failed");
    
    // Get device info
    device_t device_info;
    bool info_result = devmgr_get_device_info(device_id, &device_info);
    ASSERT(info_result, "Failed to get device info");
    ASSERT_STR_EQUAL("test_device", device_info.name, "Device name mismatch");
    ASSERT_EQUAL(DEVICE_TYPE_DISK, device_info.type, "Device type mismatch");
    
    // Add a property
    int64_t test_value = 42;
    bool prop_result = devmgr_add_property(device_id, "test_property", 
                                         PROPERTY_TYPE_INTEGER, 
                                         &test_value, 
                                         sizeof(test_value));
    ASSERT(prop_result, "Failed to add property");
    
    // Get property value
    int64_t retrieved_value;
    uint64_t size = sizeof(retrieved_value);
    bool get_result = devmgr_get_value(device_id, "test_property", 
                                     &retrieved_value, &size);
    ASSERT(get_result, "Failed to get property value");
    ASSERT_EQUAL(42, retrieved_value, "Property value mismatch");
}

// Test case for device listing
TEST_CASE(test_device_listing) {
    // Initialize the device manager
    devmgr_init();
    
    // Register a device type
    devmgr_register_type("test_type", "Test device type");
    
    // Register multiple devices
    uint64_t device1 = devmgr_register_device("device1", DEVICE_TYPE_DISK, 1);
    uint64_t device2 = devmgr_register_device("device2", DEVICE_TYPE_DISK, 1);
    printf("Registered device1: %llu, device2: %llu\n", device1, device2);
    
    // Get device count
    uint64_t count = devmgr_get_device_count(DEVICE_TYPE_DISK);
    printf("Device count: %llu\n", count);
    ASSERT_EQUAL(2, count, "Device count mismatch");
    
    // Get device list
    uint64_t device_ids[2];
    uint64_t list_count = 2;
    bool list_result = devmgr_get_device_list(DEVICE_TYPE_DISK, device_ids, &list_count);
    printf("Device list count: %llu\n", list_count);
    ASSERT(list_result, "Failed to get device list");
    ASSERT_EQUAL(2, list_count, "Device list count mismatch");
}

// Test suite for device manager
TEST_SUITE(device_manager_suite) {
    RUN_TEST(test_device_registration);
    RUN_TEST(test_device_listing);
}

int main() {
    printf("Running Device Manager Tests\n");
    printf("===========================\n");
    
    device_manager_suite();
    
    PRINT_TEST_RESULTS();
    
    return test_results.failed_tests == 0 ? 0 : 1;
} 