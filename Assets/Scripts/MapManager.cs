using System.Collections;
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
