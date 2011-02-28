class ApplicationController < ActionController::Base
  protect_from_forgery

	before_filter :setup_nav, :store_location
	
	helper_method :current_user

	def setup_nav
		@pages = [
			%w{ Home },
			%w{ Projects projects },
			%w{ Web\ Design designs },
			%w{ Resume resume },
			%w{ Contact contact },
		]

		@nav = nav

		if (!@title) then
			@title = request.fullpath

			if @title == '/'
				@title = 'Home'
			else
				@title = @title.split('/')[1]
				@title = @title.capitalize
			end
		end

		@title =  @title.join(' : ') if @title.is_a? Array

		if @title != '' then
			@title = ' : ' + @title
		end
	end

  def nav
  end

	protected 

	def current_user_session
		return @current_user_session if defined?(@current_user_session)
		@current_user_session = UserSession.find
	end
	
	def current_user
		false
		return @current_user if defined?(@current_user)
		@current_user = current_user_session && current_user_session.record
	end

	before_filter :require_users_filter
	def require_users_filter
		if defined?(@@protected_actions)
			@@protected_actions.each do |a|
				if self.action_name == a.to_s
					require_user
				end
			end
		end
	end

	def self.require_user(*actions)
		logger.info("require_user");

		@@protected_actions = actions
	end

	def require_user
		logger.info("instance require_user")
		unless current_user
			store_location
			redirect_to '/login', :notice => "You must be logged in to access this page"
			return false
		end
	end

	def require_no_user
		if current_user
			store_location
			redirect_to '/', :notice => "You must be logged out to access this page"
			return false
		end
	end
	
	def store_location
		if request.method == 'GET' and !request.fullpath.match /^\/(reset-password|login|logout|user-session)/
			logger.info("setting last uri to #{request.fullpath}")
			session[:return_to] = request.fullpath
		end
	end
 
	def last_uri
		session[:return_to] || '/'
	end


end
