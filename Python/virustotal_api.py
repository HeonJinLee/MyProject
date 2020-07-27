from __future__ import print_function
import json
import hashlib
from virus_total_apis import PublicApi as VirusTotalPublicApi

API_KEY = 'your api key'

check = "5be07406f0e6f27cfc89cd40d747e28a"

vt = VirusTotalPublicApi(API_KEY)

response = vt.get_file_report(check)
print(json.dumps(response, sort_keys=False, indent=4))
