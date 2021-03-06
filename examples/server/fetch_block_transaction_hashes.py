import sys
import binascii
import zmq.asyncio
import asyncio

loop = zmq.asyncio.ZMQEventLoop()
asyncio.set_event_loop(loop)

import libbitcoin.server
context = libbitcoin.server.Context()

async def main():
    client = context.Client("tcp://gateway.unsystem.net:9091")

    idx = "000000000000048b95347e83192f69cf0366076336c639f9b7228e9ba171342e"
    idx = bytes.fromhex(idx)

    ec, hashes = await client.block_transaction_hashes(idx)
    if ec:
        print("Couldn't fetch block_transaction_hashes:", ec, file=sys.stderr)
        context.stop_all()
        return
    for hash in hashes:
        print(binascii.hexlify(hash))

    context.stop_all()

if __name__ == '__main__':
    tasks = [
        main(),
    ]
    tasks.extend(context.tasks())
    loop.run_until_complete(asyncio.wait(tasks))
    loop.close()

