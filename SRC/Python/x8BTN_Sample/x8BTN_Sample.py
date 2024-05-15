import smbus
import time

# PCA9557 I2C address
PCA9557_ADDRESS = 0x19

# PCA9557 register addresses
INPUT_PORT = 0x00
OUTPUT_PORT = 0x01
POLARITY_INVERSION = 0x02
CONFIGURATION = 0x03

# Register initial values
CONFIG_INIT_VALUE = 0xFF            # IIII OOOO
CONFIG_INVERSION_VALUE = 0xFF       # 1111 1111

# Initialize I2C bus
bus = smbus.SMBus(1)

def setup_pca9557():
    bus.write_byte_data(PCA9557_ADDRESS, CONFIGURATION, CONFIG_INIT_VALUE)
    bus.write_byte_data(PCA9557_ADDRESS, POLARITY_INVERSION, CONFIG_INVERSION_VALUE)

def read_input_port():
    return bus.read_byte_data(PCA9557_ADDRESS, INPUT_PORT)

def main():
    setup_pca9557()

    try:
        while True:
            input_state = read_input_port()
            btn = [(input_state >> bit) & 1 for bit in range(8)]
            print("BTN: ", " ".join(str(bit) for bit in btn))
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("\nFinish!")

if __name__ == '__main__':
    main()
