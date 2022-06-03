window.BENCHMARK_DATA = {
  "lastUpdate": 1654215693331,
  "repoUrl": "https://github.com/gregbartell/wordler",
  "entries": {
    "C++ Benchmark": [
      {
        "commit": {
          "author": {
            "email": "gregorybartell@gmail.com",
            "name": "Gregory Bartell",
            "username": "gregbartell"
          },
          "committer": {
            "email": "gregbartell@users.noreply.github.com",
            "name": "gregbartell",
            "username": "gregbartell"
          },
          "distinct": true,
          "id": "ee775979ef2f9dc7c66e4a37161194674669e467",
          "message": "Fix Build Github Action",
          "timestamp": "2022-01-29T16:58:24-06:00",
          "tree_id": "d72315e95890c147213326b73526377a74a34a11",
          "url": "https://github.com/gregbartell/wordler/commit/ee775979ef2f9dc7c66e4a37161194674669e467"
        },
        "date": 1643497765550,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_SolverGetBestGuess/100",
            "value": 74798253.55555648,
            "unit": "ns/iter",
            "extra": "iterations: 9\ncpu: 74784788.8888889 ns\nthreads: 1"
          },
          {
            "name": "BM_WordleGetHint/1000",
            "value": 505867761.99999404,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 504895899.99999994 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "gregorybartell@gmail.com",
            "name": "Gregory Bartell",
            "username": "gregbartell"
          },
          "committer": {
            "email": "gregbartell@users.noreply.github.com",
            "name": "gregbartell",
            "username": "gregbartell"
          },
          "distinct": true,
          "id": "ee775979ef2f9dc7c66e4a37161194674669e467",
          "message": "Fix Build Github Action",
          "timestamp": "2022-01-29T16:58:24-06:00",
          "tree_id": "d72315e95890c147213326b73526377a74a34a11",
          "url": "https://github.com/gregbartell/wordler/commit/ee775979ef2f9dc7c66e4a37161194674669e467"
        },
        "date": 1643497784569,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_SolverGetBestGuess/100",
            "value": 63812279.10000007,
            "unit": "ns/iter",
            "extra": "iterations: 10\ncpu: 63798470 ns\nthreads: 1"
          },
          {
            "name": "BM_WordleGetHint/1000",
            "value": 470440116.9999954,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 470418150 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "gregorybartell@gmail.com",
            "name": "Gregory Bartell",
            "username": "gregbartell"
          },
          "committer": {
            "email": "gregorybartell@gmail.com",
            "name": "Gregory Bartell",
            "username": "gregbartell"
          },
          "distinct": true,
          "id": "5fe3cce0096e45df163af117de808dbb2cd562a2",
          "message": "Clean Up Errant Comments, Add New Ones",
          "timestamp": "2022-01-29T19:04:51-06:00",
          "tree_id": "0892808af16ab641086d33a3335ca104dcabaa75",
          "url": "https://github.com/gregbartell/wordler/commit/5fe3cce0096e45df163af117de808dbb2cd562a2"
        },
        "date": 1643504789519,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_SolverGetBestGuess/100",
            "value": 67744145.40000038,
            "unit": "ns/iter",
            "extra": "iterations: 10\ncpu: 67711420 ns\nthreads: 1"
          },
          {
            "name": "BM_WordleGetHint/1000",
            "value": 434869122.000002,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 434814349.9999999 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "gregorybartell@gmail.com",
            "name": "Gregory Bartell",
            "username": "gregbartell"
          },
          "committer": {
            "email": "gregbartell@users.noreply.github.com",
            "name": "gregbartell",
            "username": "gregbartell"
          },
          "distinct": true,
          "id": "4d54847f61712b2b080b66338753e1588e96fcc0",
          "message": "Use 1-Byte Hints\n\nChanges the way hints are stored internally to use less memory.\nThis is a significant performance improvement: the time taken on the\nhint generation benchmark is reduced by ~37% and the time taken on the\noverall guess generation test is reduced by ~50%.\n\nThis change removes support for Wordle variants using word lengths other\nthan 5.",
          "timestamp": "2022-06-02T19:20:18-05:00",
          "tree_id": "b6ba3cfafabe965da102ffafa1371cf24d6fdc03",
          "url": "https://github.com/gregbartell/wordler/commit/4d54847f61712b2b080b66338753e1588e96fcc0"
        },
        "date": 1654215692989,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_SolverGetBestGuess/100",
            "value": 39240506.05882331,
            "unit": "ns/iter",
            "extra": "iterations: 17\ncpu: 39228147.058823526 ns\nthreads: 1"
          },
          {
            "name": "BM_WordleGetHint/1000",
            "value": 234176815.66667172,
            "unit": "ns/iter",
            "extra": "iterations: 3\ncpu: 234044966.66666663 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}