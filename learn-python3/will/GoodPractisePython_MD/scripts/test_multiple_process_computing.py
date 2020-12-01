import multiprocessing
import concurrent.futures
from datetime import datetime
from functools import partial

def timethis(func):
    def wrapper(*args, **kwargs):
        begin = datetime.now()
        res = func(*args, **kwargs)
        print(f'{func.__name__} costs:{datetime.now() - begin}')
        return res
    return wrapper

def square_sums(nums, idxs):
    return sum(i*i for i in nums[idxs])

def split_data(nums, part_num):
    batch = len(nums)//part_num
    samples = [slice(i*batch, i*batch+batch) for i in range(part_num-1)]
    samples.append(slice(samples[-1].stop, -1))
    return samples

@timethis
def multiple_process(nums):
    cpu_num = multiprocessing.cpu_count()
    print(f'multiple processes: {cpu_num}')
    samples = split_data(nums, cpu_num)

    with concurrent.futures.ProcessPoolExecutor() as pool:
        res = pool.map(partial(square_sums, nums), samples)
        print(sum(res))

@timethis
def multiple_threads(nums):
    part_num = 4
    print(f'multiple threads:{part_num}')
    samples = split_data(nums, part_num)

    with concurrent.futures.ThreadPoolExecutor(max_workers=part_num) as pool:
        res = pool.map(partial(square_sums, nums), samples)
        print(sum(res))

@timethis
def single_process(nums):
    print('single process, single thread')
    print(square_sums(nums, slice(0, -1)))

if __name__ == '__main__':
    numbers = range(100_000_000)
    import sys
    concurrent_type = sys.argv[1]
    if concurrent_type == 'multiple_processing':
        multiple_process(numbers)
    elif concurrent_type == 'multiple_threads':
        multiple_threads(numbers)
    else:
        single_process(numbers)


