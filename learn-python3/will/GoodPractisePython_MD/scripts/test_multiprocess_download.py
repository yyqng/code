import requests
import multiprocessing
import concurrent.futures
import time

session = None
len_queue = multiprocessing.Queue()

def set_global_session():
    global session
    if not session:
        session = requests.Session()

def download_site(url):
    with session.get(url) as response:
        name = multiprocessing.current_process().name
        print(f"{name}:Read {len(response.content)} from {url}")
        return len(response.content)

def download_all_sites(sites):
    # Both the following ways are OK
    # with multiprocessing.Pool(initializer=set_global_session) as pool:
    with concurrent.futures.ProcessPoolExecutor(initializer=set_global_session) as pool:
        res = pool.map(download_site, sites)
        print('total_len:', sum(res))


if __name__ == "__main__":
    sites = [
        "https://www.jython.org",
        "http://olympus.realpython.org/dice",
    ] * 10
    start_time = time.time()
    download_all_sites(sites)
    duration = time.time() - start_time
    print(f"Downloaded {len(sites)} in {duration} seconds")