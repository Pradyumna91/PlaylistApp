#pragma once

struct Node
{
	int item;
	Node* next;
};

ref class Playlist
{
private:
	Node* head;
	int currentlyPlayingTrackIndex;
	int totalNumberOfTracks;

	void displayPlaylist();
public:
	Playlist();
	void create(int numberOfTracks);
	void deleteTrackAtPosition(int position);
	void insertTrackAtPosition(int position, int trackId);
	void shuffle();
	void playTrack(int position);
	
};

