<<<<<<< HEAD
﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapManager : MonoBehaviour {
    public static MapManager Instance;

    public Transform enemyEnterPoint;
    public Transform enemyExitPoint;

    public int width = 17;
    public int height = 13;

    public PF.Grid grid { get; private set; }

    int[,] map;
    bool[,] walkableMap;

    void Awake() {
        if (Instance == null) Instance = this;

        map = new int[height, width];
        walkableMap = new bool[height, width];

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                walkableMap[i, j] = (map[i, j] == 0);
            }
        }

        grid = new PF.Grid(walkableMap);
    }

    void UpdateGridMap() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                walkableMap[i, j] = (map[i, j] == 0);
            }
        }
        grid.UpdateGrid(walkableMap);
    }

    public Vector2 GridToWorldPoint(Vector2Int gp) {
        return (gp - (Vector2)transform.position) - new Vector2(width / 2, height / 2);
    }

    public Vector2Int WorldToGridPoint(Vector2 wp) {
        return Vector2Int.FloorToInt(wp - (Vector2)transform.position) + new Vector2Int(width / 2, height / 2);
    }
}
=======
﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapManager : MonoBehaviour {
    public static MapManager Instance;

    public int width;
    public int height;

    public GameObject tile;
	// Use this for initialization
	void Awake () {
        if (Instance == null) Instance = this;
	}

    void Start() {
        for(int i=0; i<17; i++)
        {
            for(int j=0; j<13; j++)
            {
                Instantiate(tile, new Vector2((i - 8.0f) * 0.5f, (j - 6.0f) * 0.5f), Quaternion.identity);
            }
        }
    }
    // Update is called once per frame
    void Update () {
		
	}
}
>>>>>>> 32418fcef269c19f460fcf2c0b5057e99a4d8159
