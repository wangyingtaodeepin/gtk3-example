#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
from dogtail.tree import *

example4 = root.application("example-4", "")
wangyingtao = example4.child("Button 1")
wangyingtao2 = example4.child("Button 2")

for i in range(10):
    wangyingtao.click()
    sleep(1)
    wangyingtao2.click()
    sleep(1)
