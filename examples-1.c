// to avoid casting the pointer to the controller's ABI
typedef struct
{
    union
    {
        DeviceControllerA ac;
        DeviceControllerB bc;
    };
    void* io;
} Device;

typedef struct
{
    uint32 type;
    union
    {
        KeyboardController* keyboard;
        FloppyDriveController* floppy;
        MyKittyFeeder* kitty_feeder;
    };
    void* io
} Device;


Device* device = get_device("0:0a:bf:3d");
if (device->type == DEVICE_TYPE_KITTY_FEEDER) {
    device->kitty_feeder->feed_my_kitty(device->io)
} else if (device->type == DEVICE_TYPE_KEYBOARD) {
    notify_keyboard_state(device->keyboard->read_state(device->io));
}

((KittyFeederABI *)device->controller)->feed_my_kitty(device->io)
