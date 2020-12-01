
from aiohttp import web
import asyncio
import random

random.seed(0)

async def handle(request):
    return web.Response(text='Hello')

async def random_int_handle(request):
    text = f'{random.randint(0, 100)}'
    return web.Response(text=text)


def main():
    app = web.Application()
    app.add_routes([web.get('/random_int', random_int_handle),
                    web.get('/{name}', handle)])

    web.run_app(app, host="127.0.0.1", port=8811)


if __name__ == '__main__':
    main()
