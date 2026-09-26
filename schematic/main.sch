{
  "version": 1,
  "symbols": [
    {
      "id": "esp32_1",
      "type": "reg:esp32-devkit",
      "ref": "U1",
      "x": 18,
      "y": 30,
      "rotation": 0,
      "mirror": false
    },
    {
      "id": "hc_1",
      "type": "reg:hc-sr04",
      "ref": "U2",
      "x": 40,
      "y": 17,
      "rotation": 0,
      "mirror": false
    },
    {
      "id": "r_top",
      "type": "resistor",
      "ref": "R1",
      "x": 13,
      "y": 15,
      "rotation": 0,
      "value": "2k",
      "mirror": false
    },
    {
      "id": "r_bottom",
      "type": "resistor",
      "ref": "R2",
      "x": 66,
      "y": 70,
      "rotation": 0,
      "value": "3.9k",
      "mirror": false
    }
  ],
  "wires": [
    {
      "id": "bbs_w_0",
      "points": [
        {
          "x": 12,
          "y": 24
        },
        {
          "x": 18,
          "y": 24
        },
        {
          "x": 18,
          "y": 18
        },
        {
          "x": 34,
          "y": 18
        }
      ],
      "net": "N_IO32"
    },
    {
      "id": "bbs_w_1",
      "points": [
        {
          "x": 12,
          "y": 26
        },
        {
          "x": 15,
          "y": 26
        },
        {
          "x": 15,
          "y": 84
        },
        {
          "x": 13,
          "y": 84
        },
        {
          "x": 13,
          "y": 18
        }
      ],
      "net": "N_IO33"
    },
    {
      "id": "bbs_w_2",
      "points": [
        {
          "x": 12,
          "y": 26
        },
        {
          "x": 15,
          "y": 26
        },
        {
          "x": 15,
          "y": 27
        },
        {
          "x": 66,
          "y": 27
        },
        {
          "x": 66,
          "y": 67
        }
      ],
      "net": "N_IO33"
    },
    {
      "id": "bbs_w_3",
      "points": [
        {
          "x": 24,
          "y": 12
        },
        {
          "x": 50,
          "y": 12
        },
        {
          "x": 50,
          "y": 81
        },
        {
          "x": 82,
          "y": 81
        },
        {
          "x": 82,
          "y": 18
        },
        {
          "x": 46,
          "y": 18
        }
      ],
      "net": "0"
    },
    {
      "id": "bbs_w_4",
      "points": [
        {
          "x": 24,
          "y": 12
        },
        {
          "x": 50,
          "y": 12
        },
        {
          "x": 50,
          "y": 78
        },
        {
          "x": 66,
          "y": 78
        },
        {
          "x": 66,
          "y": 73
        }
      ],
      "net": "0"
    },
    {
      "id": "bbs_w_5",
      "points": [
        {
          "x": 46,
          "y": 18
        },
        {
          "x": 82,
          "y": 18
        },
        {
          "x": 82,
          "y": 81
        },
        {
          "x": 18,
          "y": 81
        },
        {
          "x": 18,
          "y": 38
        },
        {
          "x": 12,
          "y": 38
        }
      ],
      "net": "0"
    },
    {
      "id": "bbs_w_6",
      "points": [
        {
          "x": 46,
          "y": 18
        },
        {
          "x": 82,
          "y": 18
        },
        {
          "x": 82,
          "y": 81
        },
        {
          "x": 50,
          "y": 81
        },
        {
          "x": 50,
          "y": 24
        },
        {
          "x": 24,
          "y": 24
        }
      ],
      "net": "0"
    },
    {
      "id": "bbs_w_7",
      "points": [
        {
          "x": 12,
          "y": 48
        },
        {
          "x": 12,
          "y": 15
        },
        {
          "x": 50,
          "y": 15
        },
        {
          "x": 50,
          "y": 16
        },
        {
          "x": 34,
          "y": 16
        }
      ],
      "net": "VIN"
    },
    {
      "id": "bbs_w_8",
      "points": [
        {
          "x": 46,
          "y": 16
        },
        {
          "x": 13,
          "y": 16
        },
        {
          "x": 13,
          "y": 12
        }
      ],
      "net": "N12"
    }
  ],
  "junctions": [
    {
      "id": "j_15_26",
      "x": 15,
      "y": 26
    },
    {
      "id": "j_15_27",
      "x": 15,
      "y": 27
    },
    {
      "id": "j_13_26",
      "x": 13,
      "y": 26
    },
    {
      "id": "j_50_12",
      "x": 50,
      "y": 12
    },
    {
      "id": "j_50_81",
      "x": 50,
      "y": 81
    },
    {
      "id": "j_82_81",
      "x": 82,
      "y": 81
    },
    {
      "id": "j_82_18",
      "x": 82,
      "y": 18
    },
    {
      "id": "j_46_18",
      "x": 46,
      "y": 18
    },
    {
      "id": "j_50_78",
      "x": 50,
      "y": 78
    },
    {
      "id": "j_50_24",
      "x": 50,
      "y": 24
    },
    {
      "id": "j_50_18",
      "x": 50,
      "y": 18
    }
  ],
  "netLabels": [
    {
      "id": "bbs_nl_0",
      "name": "N_IO32",
      "x": 12,
      "y": 24,
      "owner": "esp32_1",
      "anchor": "end"
    },
    {
      "id": "bbs_nl_1",
      "name": "N_IO33",
      "x": 12,
      "y": 26,
      "owner": "esp32_1",
      "anchor": "end"
    },
    {
      "id": "bbs_nl_2",
      "name": "GND",
      "x": 24,
      "y": 12,
      "owner": "esp32_1",
      "anchor": "start"
    },
    {
      "id": "bbs_nl_3",
      "name": "VIN",
      "x": 12,
      "y": 48,
      "owner": "esp32_1",
      "anchor": "end"
    },
    {
      "id": "bbs_nl_4",
      "name": "N12",
      "x": 46,
      "y": 16,
      "owner": "hc_1",
      "anchor": "start"
    }
  ],
  "probes": [],
  "directives": [],
  "breadboardSync": {
    "sourceHash": "7923:-2063675170",
    "symbolIds": [
      "esp32_1",
      "hc_1",
      "r_top",
      "r_bottom"
    ],
    "wireIds": [
      "bbs_w_0",
      "bbs_w_1",
      "bbs_w_2",
      "bbs_w_3",
      "bbs_w_4",
      "bbs_w_5",
      "bbs_w_6",
      "bbs_w_7",
      "bbs_w_8"
    ],
    "netLabelIds": [
      "bbs_nl_0",
      "bbs_nl_1",
      "bbs_nl_2",
      "bbs_nl_3",
      "bbs_nl_4"
    ]
  }
}