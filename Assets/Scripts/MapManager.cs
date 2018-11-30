using System.Collections;
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
