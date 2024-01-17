import asyncio
from bleak import BleakClient
from bleak.backends.characteristic import BleakGATTCharacteristic

async def run(address):
    async with BleakClient(address) as client:
        services = client.services
        for service in services:
            # print(f"Service UUID Type: {type(service.uuid)}")
            print(f"Service UUID: {service.uuid}")
            for char in service.characteristics:
                print(f"Characteristic UUID: {char.uuid}")
                # if str(char.uuid) == "00000007-0000-3512-2118-0009af100700":
                #     print(f"Attributes of characteristic {char.uuid}:")
                #     descriptors = char.descriptors
                #     for descriptor in descriptors:
                #         print(descriptor.uuid)
                #     attributes = vars(char)
                #     for name, value in attributes.items():
                #         print(f" {name}: {value}")
                #     data = await client.read_gatt_char(descriptor)
                #     print(f" Data: {data}")
                        

mi_band_address = 'D0:4E:AD:C0:AF:7D'
asyncio.run(run(mi_band_address))

