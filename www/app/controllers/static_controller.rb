class StaticController < ApplicationController

  caches_page :resume, :contact

  def nav
    @nav
  end

  def resume
    @nav = 'resume'
  end

#  def juggling
#    @nav = 'juggling'
#  end

  def contact
    @nav = 'contact'
  end

#  def links
#    @nav = 'links'
#  end


end

