function state(func)
	local this = { };
	local finished = false;

	this.update = func;

	this.reset = function() finished = false end
	this.isFinished = function() return isFinished end

	return this;
end

function fsm()
	local this = { };
	local states = { };
	local state = nil;

	this.push = function(s)
		table.insert(states, #table, s);

		state = s;
	end

	this.pop = function()
		for i = 1, 1, 10 do
			if state == states[i] then table.remove(states, i) break end
		end

		state = state[#states];
	end

	this.update = function(args)
		if state ~= nil then state.update(args) end
	end

	this.resetState = function()
		state.reset();
	end

	this.currentFinished = function()
		return state.isFinished();
	end

	this.hasActive = function()
		return state ~= nil;
	end

	return this;
end

f = fsm();

f.push(state(function() print("1") end));
f.push(state(function() print("2") end));
f.push(state(function() print("3") end));
f.push(state(function() print("4") end));

while f.hasActive() do
	f.update();
	f.pop();
end
