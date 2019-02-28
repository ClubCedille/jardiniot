import React from 'react';
import { Link } from 'react-router-dom';

export default () => (
  <div id="notfound">
		<div className="notfound">
			<div className="notfound-404">
				<h1>Oups!</h1>
			</div>
			<h2>404 - Page inexistante</h2>
			<p>La page que vous recherchez a peut-être été supprimée si son nom a été modifié ou est temporairement indisponible.</p>
			<br/>
			<Link to="/">Revenir à l'accueil</Link>
		</div>
	</div>
);