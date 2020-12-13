## 1. Improve the following codes to be pythonic(Required)

```python
def append_student(students):
    family_name_2_names = {}
    for family_name, last_name in students:
        if family_name not in family_name_2_names:
            family_name_2_names[family_name] = [last_name]
        else:
            family_name_2_names[family_name].append(last_name)

def append_student_v2(students):
    # TODO
    pass

def get_even_ones(names):
    results = []
    idx = 0
    for n in names:
        if idx % 2 == 0:
            results.append(n)
    return results

def get_even_ones_v2(names):
    # TODO
    pass

def print_all(boys, girls):
    for b in boys:
        print(b)

    for g in girls:
        print(g)
        
def print_all_v2(boys, girls):
    # TODO
    pass

def filter_error_msg(input_file, output_file):
    with open(input_file) as f_in:
        with open(output_file, 'w') as f_out:
            for line in f_in:
                if 'error' in line:
                    f_out.write(line)

def filter_error_msg_v2(input_file, output_file):
    # TODO
    pass

# add code to support '<=', '>', '>=' too
class Student:
    def __eq__(self, other):
        return ((self.lastname.lower(), self.firstname.lower()) ==
                (other.lastname.lower(), other.firstname.lower()))

    def __lt__(self, other):
        return ((self.lastname.lower(), self.firstname.lower()) <
                (other.lastname.lower(), other.firstname.lower()))


class Session:
    def __init__(self, sequence_of_numbers):
        self._data = sequence_of_numbers
        self._mean = None

    @property
    def mean(self):
        if not self._mean:
            self._mean = sum(self._data)/len(self._data)
        return self._mean
    
class Session_v2:
    # TODO
    pass
```

## 2. Improve client code to decrease respont time(Optional)
- Server

```python
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

```

- Client

```python
import requests

def query_sites(sites):
    results = []
    for s in sites:
        res = requests.get(s)
        results.append(res.text)
    print(results)
   
def main_requests():
    sites = ('http://127.0.0.1:8811/random_int' for i in range(1000))
    query_sites(sites)

if __name__ == '__main__':
    main_requests()
```


## 3. Implement function `evaluate_mutau_2` to decrease the running time compared with V1.0(Optional)

```python
import numpy as np
import random
import time
import functools

def timethis(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        begin = time.time()
        res = func(*args, **kwargs)
        print(f'func.__name__ costs {time.time()-begin}')
        return res
    return wrapper


def ReconstructFieldOrderPerWafer_np(mu1, tau1, mu2, tau2, Dose=30.0, RT=0.3969, Image_Size_X=26.0, Image_Size_Y=33.0,
                                     Number_of_Fields=137.0, th=15.2, tc=3.6, lot_size=25):
    mu1 = float(mu1)
    tau1 = float(tau1)
    mu2 = float(mu2)
    tau2 = float(tau2)

    S = Image_Size_X * Image_Size_Y * Number_of_Fields * 10 ** (-2)
    Power1 = np.multiply(RT * S * Dose * 10 ** (-3) / th, mu1)
    Power2 = np.multiply(RT * S * Dose * 10 ** (-3) / th, mu2)

    alpha1 = np.exp(-th / tau1)
    alpha2 = np.exp(-th / tau2)
    beta1 = np.exp(-tc / tau1)
    beta2 = np.exp(-tc / tau2)

    output_list = []

    LHFF_1 = np.multiply(Power1, np.subtract(1.0, alpha1))
    LHFF_2 = np.multiply(Power2, np.subtract(1.0, alpha2))

    for w in range(lot_size):  # loop through all wafers
        if w == 0:
            output_list.append(np.zeros(np.shape(LHFF_1)))
            output_list.append(np.add(LHFF_1, LHFF_2))

        else:
            LHFF_start_1 = np.multiply(np.multiply(LHFF_1, beta1),
                                       np.divide(np.subtract(1.0, np.power(np.multiply(alpha1, beta1), w)),
                                                 np.subtract(1.0, np.multiply(alpha1, beta1))))
            LHFF_start_2 = np.multiply(np.multiply(LHFF_2, beta2),
                                       np.divide(np.subtract(1.0, np.power(np.multiply(alpha2, beta2), w)),
                                                 np.subtract(1.0, np.multiply(alpha2, beta2))))

            LHFF_end_1 = np.multiply(LHFF_1,
                                     np.divide(np.subtract(1.0, np.power(np.multiply(alpha1, beta1), np.add(1.0, w))),
                                               np.subtract(1.0, np.multiply(alpha1, beta1))))
            LHFF_end_2 = np.multiply(LHFF_2,
                                     np.divide(np.subtract(1.0, np.power(np.multiply(alpha2, beta2), np.add(1.0, w))),
                                               np.subtract(1.0, np.multiply(alpha2, beta2))))

            output_list.append(np.add(LHFF_start_1, LHFF_start_2))
            output_list.append(np.add(LHFF_end_1, LHFF_end_2))

    return [float(e) for e in output_list]


def generate_dummy_data():
    """return a dict: {name, [truth_data, prediction_data]}"""
    num = 10000
    random.seed(0)
    res = {}
    for i in range(num):
        res[f'name{i}'] = [[random.randint(20, 2000) for i in range(4)], [random.randint(20, 2000) for i in range(4)]]
    return res


def evaluate_mutau(truth_pred_mutau_dict):
    deviation_list = []
    for name, (truth_data, pred_data) in truth_pred_mutau_dict.items():
        truth = ReconstructFieldOrderPerWafer_np(*truth_data)
        pred = ReconstructFieldOrderPerWafer_np(*pred_data)
        for t, p in zip(truth, pred):
            deviation_list.append(abs(t-p))
    max_deviation = max(deviation_list)
    mean_deviation = sum(deviation_list)/len(truth_pred_mutau_dict)
    return max_deviation, mean_deviation

def evaluate_mutau_2(truth_pred_mutau_dict):
    # TODO
    pass

@timethis
def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('-version', choices=['1.0', '2.0'], type=str, default='1.0')
    opts = parser.parse_args()

    truth_pred_mutau_dict = generate_dummy_data()
    if opts.version == '1.0':
        max_dev, mean_dev = evaluate_mutau(truth_pred_mutau_dict)
    else:
        max_dev, mean_dev = evaluate_mutau_2(truth_pred_mutau_dict)
    print(f"max_deviation:{max_dev}, mean_deviation:{mean_dev}")


if __name__ == '__main__':
    main()
```
