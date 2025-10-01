import React, { useState } from 'react';
import { Leaf, Plus, Trash2, Award } from 'lucide-react';

export default function EcoTracker() {
  const [activities, setActivities] = useState([]);
  const [showForm, setShowForm] = useState(false);
  const [selectedActivity, setSelectedActivity] = useState('');
  const [points, setPoints] = useState(0);

  const ecoActivities = [
    { name: 'Used reusable bag', points: 5, icon: '🛍️' },
    { name: 'Recycled waste', points: 10, icon: '♻️' },
    { name: 'Biked instead of driving', points: 15, icon: '🚴' },
    { name: 'Used public transport', points: 10, icon: '🚌' },
    { name: 'Saved water', points: 8, icon: '💧' },
    { name: 'Planted a tree', points: 20, icon: '🌳' },
    { name: 'Composted food waste', points: 12, icon: '🌱' },
    { name: 'Used reusable bottle', points: 5, icon: '🍶' },
  ];

  const addActivity = () => {
    if (!selectedActivity) return;
    
    const activity = ecoActivities.find(a => a.name === selectedActivity);
    const newActivity = {
      id: Date.now(),
      ...activity,
      date: new Date().toLocaleDateString(),
      time: new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' })
    };
    
    setActivities([newActivity, ...activities]);
    setPoints(points + activity.points);
    setShowForm(false);
    setSelectedActivity('');
  };

  const deleteActivity = (id, activityPoints) => {
    setActivities(activities.filter(a => a.id !== id));
    setPoints(points - activityPoints);
  };

  return (
    <div className="min-h-screen bg-gradient-to-b from-green-50 to-emerald-100 pb-20">
      {/* Header */}
      <div className="bg-green-600 text-white p-6 rounded-b-3xl shadow-lg">
        <div className="flex items-center justify-between">
          <div className="flex items-center gap-3">
            <Leaf className="w-8 h-8" />
            <h1 className="text-2xl font-bold">Eco Tracker</h1>
          </div>
          <div className="flex items-center gap-2 bg-green-700 px-4 py-2 rounded-full">
            <Award className="w-5 h-5" />
            <span className="font-bold text-lg">{points}</span>
          </div>
        </div>
        <p className="mt-2 text-green-100 text-sm">Track your eco-friendly actions</p>
      </div>

      {/* Add Activity Button */}
      <div className="px-6 mt-6">
        <button
          onClick={() => setShowForm(!showForm)}
          className="w-full bg-green-600 text-white py-4 rounded-2xl font-semibold flex items-center justify-center gap-2 shadow-lg hover:bg-green-700 transition"
        >
          <Plus className="w-5 h-5" />
          Log Eco Activity
        </button>
      </div>

      {/* Activity Form */}
      {showForm && (
        <div className="mx-6 mt-4 bg-white p-6 rounded-2xl shadow-lg">
          <h3 className="font-semibold text-gray-800 mb-4">Select an activity:</h3>
          <div className="space-y-2 mb-4">
            {ecoActivities.map((activity) => (
              <button
                key={activity.name}
                onClick={() => setSelectedActivity(activity.name)}
                className={`w-full p-4 rounded-xl border-2 transition text-left flex items-center justify-between ${
                  selectedActivity === activity.name
                    ? 'border-green-500 bg-green-50'
                    : 'border-gray-200 hover:border-green-300'
                }`}
              >
                <div className="flex items-center gap-3">
                  <span className="text-2xl">{activity.icon}</span>
                  <span className="font-medium">{activity.name}</span>
                </div>
                <span className="text-green-600 font-bold">+{activity.points}</span>
              </button>
            ))}
          </div>
          <div className="flex gap-2">
            <button
              onClick={() => {
                setShowForm(false);
                setSelectedActivity('');
              }}
              className="flex-1 py-3 border-2 border-gray-300 rounded-xl font-semibold hover:bg-gray-50"
            >
              Cancel
            </button>
            <button
              onClick={addActivity}
              disabled={!selectedActivity}
              className="flex-1 py-3 bg-green-600 text-white rounded-xl font-semibold hover:bg-green-700 disabled:bg-gray-300 disabled:cursor-not-allowed"
            >
              Add
            </button>
          </div>
        </div>
      )}

      {/* Activities List */}
      <div className="px-6 mt-6">
        <h2 className="text-xl font-bold text-gray-800 mb-4">Recent Activities</h2>
        {activities.length === 0 ? (
          <div className="bg-white p-8 rounded-2xl text-center text-gray-500">
            <Leaf className="w-12 h-12 mx-auto mb-3 text-gray-300" />
            <p>No activities logged yet</p>
            <p className="text-sm mt-1">Start tracking your eco-friendly actions!</p>
          </div>
        ) : (
          <div className="space-y-3">
            {activities.map((activity) => (
              <div
                key={activity.id}
                className="bg-white p-4 rounded-2xl shadow-md flex items-center justify-between"
              >
                <div className="flex items-center gap-3">
                  <span className="text-3xl">{activity.icon}</span>
                  <div>
                    <p className="font-semibold text-gray-800">{activity.name}</p>
                    <p className="text-sm text-gray-500">
                      {activity.date} at {activity.time}
                    </p>
                  </div>
                </div>
                <div className="flex items-center gap-3">
                  <span className="text-green-600 font-bold">+{activity.points}</span>
                  <button
                    onClick={() => deleteActivity(activity.id, activity.points)}
                    className="text-red-500 hover:bg-red-50 p-2 rounded-lg transition"
                  >
                    <Trash2 className="w-5 h-5" />
                  </button>
                </div>
              </div>
            ))}
          </div>
        )}
      </div>

      {/* Stats Footer */}
      {activities.length > 0 && (
        <div className="mx-6 mt-6 bg-white p-6 rounded-2xl shadow-lg">
          <h3 className="font-semibold text-gray-800 mb-3">Your Impact</h3>
          <div className="grid grid-cols-2 gap-4">
            <div className="text-center p-4 bg-green-50 rounded-xl">
              <p className="text-3xl font-bold text-green-600">{activities.length}</p>
              <p className="text-sm text-gray-600 mt-1">Activities</p>
            </div>
            <div className="text-center p-4 bg-emerald-50 rounded-xl">
              <p className="text-3xl font-bold text-emerald-600">{points}</p>
              <p className="text-sm text-gray-600 mt-1">Total Points</p>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
